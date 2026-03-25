from fastapi import FastAPI
from fastapi.responses import JSONResponse
import requests

app = FastAPI()

API_KEY = "YOUR_GEMINI_API_KEY"

@app.get("/")
def home():
    return {"status": "AayuGuide Server Running"}

@app.get("/ask")
def ask(age: int, symptom: str, lang: str = "English"):
    try:
        prompt = f"""
        You are a medical assistant.
        Age: {age}
        Symptoms: {symptom}

        Give simple home remedies.
        Respond in {lang}.
        """

        url = f"https://generativelanguage.googleapis.com/v1/models/gemini-1.5-flash:generateContent?key={API_KEY}"

        body = {
            "contents": [
                {
                    "parts": [{"text": prompt}]
                }
            ]
        }

        response = requests.post(url, json=body)
        data = response.json()

        text = data["candidates"][0]["content"]["parts"][0]["text"]

        return {"response": text}

    except Exception as e:
        return JSONResponse({"error": str(e)})
