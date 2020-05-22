FROM hazelcast/hazelcast:3.12.1

# Adding custom hazelcast.xml
ADD hazelcast.xml ${HZ_HOME}
ENV JAVA_OPTS -Dhazelcast.config=${HZ_HOME}/hazelcast.xml
