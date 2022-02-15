import os
import openai
# Python 3 server example from https://pythonbasics.org/webserver/
from http.server import BaseHTTPRequestHandler, HTTPServer
import time
from urllib.parse import unquote

# Parameters
openai.api_key = os.getenv("OPENAI_API_KEY")
hostName = "localhost"
# hostName = "0.0.0.0" # for deployment 
serverPort = 8080 


def say_to_babbage(stimulus):
    response = openai.Completion.create(
        engine="davinci",
        prompt=stimulus,
        temperature=0.29,
        max_tokens=64,
        top_p=1,
        frequency_penalty=0,
        presence_penalty=0,
        stop=["."]
    )
    return response["choices"][0]["text"]


# def converse_with_babbage():
#     while True:
#         stimulus = input("> ")
#         response = say_to_babbage(stimulus)
#         print(response)


def say_to_davinci(stimulus):
    response = openai.Completion.create(
        engine="davinci",
        prompt=stimulus,
        temperature=0.8, # 0.29,
        max_tokens=200
    )
    return response["choices"][0]["text"]



class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        stimulus = self.path
        stimulus = stimulus[1:] # remove forward slash from the front
        stimulus = unquote(stimulus)
        
        print("Received:", stimulus)
        response = say_to_davinci(stimulus)
        import ftfy
        response = ftfy.fix_text(response) # python unicode sucks?
        
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<!doctype html><html><head><title>GPT-3 Davinci Completion Demo</title></head>", "utf-8"))
        self.wfile.write(bytes("<p>Received: %s</p>" % stimulus, "utf-8"))
        self.wfile.write(bytes("<body>", "utf-8"))
        self.wfile.write(bytes("<p>Response: %s %s </p>" % (stimulus, response), "utf-8"))
        self.wfile.write(bytes("</body></html>", "utf-8"))



if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")
