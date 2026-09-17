from transformers import pipeline

translator = pipeline(
    "translation",
    model="Helsinki-NLP/opus-mt-en-jap"
)

result = translator("Hello, how are you today?")

print(result[0]["translation_text"])
