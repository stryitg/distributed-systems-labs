consul agent -dev -enable-script-checks
consul members
curl localhost:8500/v1/catalog/nodes -- outputs nodes
consul leave
