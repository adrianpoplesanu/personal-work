from transformers import AutoTokenizer, AutoModelForSeq2SeqLM


if __name__ == "__main__":
    model_name = "Helsinki-NLP/opus-mt-en-jap"

    tokenizer = AutoTokenizer.from_pretrained(model_name)
    model = AutoModelForSeq2SeqLM.from_pretrained(model_name)

    text = "Hello, how are you today?"
    inputs = tokenizer(text, return_tensors="pt")
    translated = model.generate(**inputs)

    print(tokenizer.decode(translated[0], skip_special_tokens=True))
