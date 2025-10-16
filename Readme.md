# ProductReview (Windows)

Tiny C++ tool that summarizes product reviews from `reviews.json`.

- `reviews.json` contains the complete json data
  
Requirements
- g++ (MinGW, TDM-GCC, DevKit, or similar) available on PATH

Setup
- Edit `productReviewLLM.cpp` and set your Groq API key (if needed):
  - change `string api_key = "YOUR_GROQ_API_KEY";`

Build (PowerShell or CMD)
```powershell
g++ productReviewLLM.cpp -o productReviewLLM.exe
```

Run
```powershell
.\productReviewLLM.exe
```

Get a Groq API key
1. Open https://console.groq.com/keys and sign in or create an account.
2. Click "Create API Key", give it a name, and copy the key value. Treat it like a secret

   
Sample Input Output
<img width="1454" height="650" alt="image" src="https://github.com/user-attachments/assets/fa257ae4-3650-447a-ac83-2326c7252cb4" />
