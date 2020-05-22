docker run -e JAVA_OPTS="-Dhazelcast.mancenter.url=http://192.168.1.12:8080/hazelcast-mancenter/ -Dhazelcast.local.publicAddress=192.168.1.12:5701" -p 5701:5701 cc56f33d00e5
g++ -o test -pthread ./src/main.cpp ./lib/libHazelcastClient3.12.1_64.a -I ./hazelcast-client/hazelcast/include/ -I ./hazelcast-client/hazelcast/generated-sources/include/ -I ./hazelcast-client/external/include/ -Wno-deprecated-declarations


