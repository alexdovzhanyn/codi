# CodI

**CodI** — short for **Cod(e) Intelligence** — is a lightweight **command-line AI code review tool** that helps developers generate structured, actionable feedback on code changes directly from the terminal.

It’s designed for quick iteration, solo workflows, and experimentation with AI-assisted review — without leaving your editor or shell.

## ✨ Features

- **AI-powered code review** using modern LLMs (OpenAI, Gemini, Claude, etc)
- **CLI-first workflow** — run reviews straight from the terminal
- **Structured output** — displays code review into formatted review UI

## 📦 Requirements

- A C++17-capable compiler (`clang++` or `g++`)
- `make`
- **OpenSSL** development headers
- A **supported AI provider API key**

## 🛠️ Build

```bash
git clone https://github.com/alexdovzhanyn/codi.git
cd codi
cp .env.example .env
# add your AI Provider's API key to .env
make
```

## Usage
```bash
# In your git repository, with unstaged, uncommitted changes
codi
```

codi will:

	1.	Read the current diff
	2.	Send the content to the AI review service
	3.	Print structured review comments to stdout
