#/usr/bin/sh

curl --request PUT --data @register_healthy.json localhost:8500/v1/agent/service/register?replace-existing-checks=true
