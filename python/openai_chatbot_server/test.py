import os
import openai

openai.api_key = os.getenv("OPENAI_API_KEY")


def say_to_davinci(stimulus):
    response = openai.Completion.create(
        engine="davinci",
        prompt=stimulus,
        temperature=0.29,
        max_tokens=30
    )
    return response["choices"][0]["text"]


def talk():
    while True:
        stimulus = input("> ")
        response = say_to_davinci(stimulus)
        print(response)


talk()
# print(response["choices"][0]["text"])