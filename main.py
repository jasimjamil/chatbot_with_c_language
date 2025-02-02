from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel
import ctypes

# Load C library (ensure the compiled chatbot.so is in the same directory)
chatbot_lib = ctypes.CDLL('./chatbot.so')

# Define input data model
class Message(BaseModel):
    question: str

# Initialize FastAPI app
app = FastAPI()

# Allow CORS for the frontend
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost"],  # Allow frontend from localhost
    allow_credentials=True,
    allow_methods=["*"],  # Allow all HTTP methods (GET, POST, etc.)
    allow_headers=["*"],  # Allow all headers
)

# Serve the frontend HTML file at the root endpoint
app.mount("/", StaticFiles(directory=".", html=True), name="static")

@app.post("/chat")
async def chat(message: Message):
    # Call C function from shared library (replace with actual function in your C code)
    chatbot_lib.searchAnswer(message.question.encode('utf-8'))
    return {"answer": "This is a sample answer from C logic"}  # Placeholder for actual C response
