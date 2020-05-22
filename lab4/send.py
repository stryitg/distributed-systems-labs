import pika
import sys

def data_from_options(options):
    durable = False
    arguments = {}
    properties = pika.BasicProperties()
    queue_name = ''
    exchange = ''
    if options[0] == 'topic':
        exchange = 'exchange'
    elif options[0] == 'p2p':
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
    
    return exchange, queue_name, durable, arguments, properties
    

options = sys.argv[1:3]
[exchange, queue_name, durable, arguments, properties] = data_from_options(options)
print(exchange, queue_name, durable, arguments, properties)

connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

if queue_name:
    channel.queue_declare(queue = queue_name, durable = durable,
                          arguments = arguments)
if exchange:
    channel.exchange_declare(exchange = exchange, exchange_type = 'fanout')

                      
def callback(ch, method, property, body):
    print('Received:', body)
    ch.basic_ack(delivery_tag = method.delivery_tag)
                      
channel.queue_declare(queue = 'client')
channel.basic_consume(queue = 'client', on_message_callback = callback)


for msg in sys.argv[3:]:    
    channel.basic_publish(exchange = exchange,
                          routing_key = queue_name,
                          body = msg,
                          properties = properties)
    print('Sent', msg)

channel.start_consuming()

connection.close()