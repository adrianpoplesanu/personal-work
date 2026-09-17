import torch
from diffusers import Krea2Pipeline

if __name__ == "__main__":
    # modelul asta nu e public, trebuie sa accept pe hugging-face si sa folosesc un access token ca sa-l folosesc
    pipe = Krea2Pipeline.from_pretrained("krea/Krea-2-Turbo", torch_dtype=torch.bfloat16).to("cuda")
    image = pipe("a fox in the snow", num_inference_steps=8, guidance_scale=0.0).images[0]
    image.save("krea2.png")

