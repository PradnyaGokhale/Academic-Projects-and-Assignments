from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel
from transformers import AutoModelForSeq2SeqLM, AutoTokenizer
import torch
import os

app = FastAPI()

# CORS
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Removed trailing slash
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Load model and tokenizer
model_ckpt = "google/pegasus-cnn_dailymail"
device = "cuda" if torch.cuda.is_available() else "cpu"
tokenizer = AutoTokenizer.from_pretrained(model_ckpt)
model = AutoModelForSeq2SeqLM.from_pretrained(model_ckpt).to(device)

# Pydantic model
class TextInput(BaseModel):
    text: str
 
# Summarization endpoint
@app.post("/summarize")
def summarize(input_data: TextInput):
    if not input_data.text.strip():
        raise HTTPException(status_code=400, detail="Input text is empty.")
    clean_text = input_data.text.replace("<n>","").strip()
    inputs = tokenizer([clean_text], max_length=1024, truncation=True, return_tensors="pt").to(device)
    summary_ids = model.generate(inputs["input_ids"], num_beams=4, max_length=150, min_length=40, length_penalty=2.0, early_stopping=True)
    summary = tokenizer.decode(summary_ids[0], skip_special_tokens=True)

    return {"summary": summary}

# Serve HTML on root
@app.get("/", response_class=HTMLResponse)
def root():
    try:
        with open("index.html", "r", encoding="utf-8") as f:
            return f.read()
    except FileNotFoundError:
        return HTMLResponse("<h1>index.html not found</h1>", status_code=404)
