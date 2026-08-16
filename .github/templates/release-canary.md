To install Talos {{version}}:

```shell
# To install for Linux / Darwin
curl -fsSL https://talos.rroessler.io/install.sh | bash --tag {{version}}

# Or alternatively on Windows
powershell -c "irm https://talos.rroessler.io/install.ps1 | iex -Tag {{version}}"
```

To upgrade to Talos {{version}}:

```shell
talos upgrade --tag {{version}}
```
