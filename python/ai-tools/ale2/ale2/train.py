from ale2.ale2config import Ale2Config
from ale2.tokenizer import CharTokenizer


def train(config: Ale2Config):
    print("training...")
    tokenizer = CharTokenizer.from_text(config.data_path)

def main():
    print("running train...")
    config = Ale2Config()
    train(config)

if __name__ == "__main__":
    main()