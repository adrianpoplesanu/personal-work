# IntelliJ MCP server setup (run app & tests from Cursor)

So Cursor (and the AI) can start/stop the app and run tests **inside IntelliJ**, configure the JetBrains MCP server as follows.

## 1. IntelliJ (2025.2+)

1. **Enable the MCP server**  
   **Settings → Tools → MCP Server**  
   - Turn **Enable MCP Server** ON.

2. **Optional but recommended (no confirmation prompts)**  
   Under **Command execution**, enable:  
   **Run shell commands or run configurations without confirmation (brave mode)**  
   Then the AI can run your run configurations (e.g. “UefaMatchesApplication”, tests) without asking each time.

3. **Get the config for Cursor**  
   - **Easiest:** In **Clients Auto-Configuration**, click **Auto-Configure** for **Cursor**.  
     Cursor’s MCP config will be updated automatically. Restart Cursor and you’re done.  
   - **Manual:** In **Manual Client Configuration**, click **Copy SSE Config**.  
     You’ll get a JSON fragment with `url` and `headers`. Use it in step 4.

## 2. Cursor (if you used “Copy SSE Config”)

1. Open MCP settings: **Cursor Settings → Tools & MCP** or **Open MCP Settings** from the command palette.
2. Either:
   - Paste the copied config into the **JetBrains IDE** server (if you add it via the UI), or  
   - Edit this project’s `.cursor/mcp.json`: replace the `jetbrains-ide` entry with the object you copied, and ensure the server has `"type": "streamableHttp"`, plus the `url` and `headers` from IntelliJ.

   Example shape (your real `url` and `headers` come from IntelliJ):

   ```json
   "jetbrains-ide": {
     "type": "streamableHttp",
     "url": "http://localhost:<port>/<path>",
     "headers": { "Authorization": "Bearer <token>" }
   }
   ```

3. **Restart Cursor** so the new MCP config is loaded.

## 3. What the AI can do

With the JetBrains MCP server connected, the AI can use IntelliJ to:

- **List run configurations** – e.g. “UefaMatchesApplication”, “Tests in …”
- **Run a configuration** – start or stop the app, run tests, with output and exit code
- **Run terminal commands** in the IDE terminal (if brave mode is on)

So you can ask in Cursor to “run the app in IntelliJ” or “run tests in IntelliJ” and the AI will call IntelliJ via MCP.

## Reference

- [IntelliJ MCP Server (official docs)](https://www.jetbrains.com/help/idea/mcp-server.html)  
- Requires **IntelliJ IDEA 2025.2 or newer**.
