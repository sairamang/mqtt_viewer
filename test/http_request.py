import requests
api_url = "http://0.0.0.0:8080/mqtt"
response = requests.get(api_url)
print(response.json())
