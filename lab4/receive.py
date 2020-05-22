import pika
import time
import sys

def data_from_options(options):
    durable = False
    arguments = {}
    properties = pika.BasicProperties()
    queue_name = ''
    exchange = ''
    if options[0] == 'topic':
        exclusive = True
        exchange = 'exchange'
    elif options[0] == 'p2p':
        exclusive = False
        if options[1] == 'basic':
            queue_name = 'queue'
        elif options[1] == 'durable':
            queue_name = 'durable-queue'
            durable = True
            properties = pika.BasicProperties(delivery_mode = 2,)
        elif options[1] == 'ttl':
            queue_name = 'ttl-queue'
            arguments = {'x-message-ttl' : 6000}
        elif options[1] == 'max-length':
            queue_name = 'max-length-queue'
            arguments = {'x-max-length' : 3}
        else:
            sys.exit('Unsuported')
    else:
        sys.exit('Unsuported')
    
    return exchange, queue_name, durable, arguments, properties, exclusive


options = sys.argv[1:3]
[exchange, queue_name, durable, arguments, properties, exclusive] = data_from_options(options)
print(exchange, queue_name, durable, arguments, properties, exclusive)

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

result = channel.queue_declare(queue = queue_name, durable = durable,
                               arguments = arguments, exclusive = exclusive)

if exchange:
    queue_name = result.method.queue
    channel.exchange_declare(exchange = exchange, exchange_type = 'fanout')
    channel.queue_bind(exchange = exchange,
                       queue = queue_name)
    

channel.queue_declare(queue = 'client')

def callback(ch, method, property, body):
    print('Received:', body)
    print('Working...')
    time.sleep(5)
    msg = 'Echo: ' + body.decode("utf-8")
    print('Sending:', msg)
    channel.basic_publish(exchange = '',
                          routing_key = 'client',
                          body = msg)
    print('Done')
    ch.basic_ack(delivery_tag = method.delivery_tag)

channel.basic_qos(prefetch_count = 1)
channel.basic_consume(queue = queue_name, on_message_callback = callback)
channel.start_consuming()