---
name: run-app-intellij
description: Starts or stops the application using the IntelliJ MCP server. Use when the user says run the application, start the app, stop the application, stop the app, run the server, or similar. Do not use Gradle or a local terminal; use the JetBrains MCP (user-jetbrains).
---

# Run / Stop Application via IntelliJ MCP

## When to apply

Apply this skill when the user asks to **run** or **stop** the application (e.g. "run the application", "start the app", "stop the app", "run the server", "stop the server", "launch the app", "kill the app").

## Rule

**Always run and stop this project's application using the IntelliJ MCP**, not `./gradlew bootRun` / terminal start or a local `kill` command.

---

## Start the application

1. **Get run configurations** (optional but recommended): Call **user-jetbrains** → **get_run_configurations** with `projectPath`: workspace root.
2. **Start**: Call **user-jetbrains** → **execute_run_configuration** with:
   - `configurationName`: **UefaMatchesApplication**
   - `projectPath`: workspace root
   - `timeout`: **15000** (ms). A timeout with Spring Boot logs in the output means the app started successfully.

---

## Stop the application

1. Call **user-jetbrains** → **execute_terminal_command** with:
   - `command`: **`lsof -ti:8080 | xargs -I {} sh -c 'ps -p {} -o command= 2>/dev/null | grep -q UefaMatchesApplication && kill {}'`**
   - `projectPath`: workspace root
   - `executeInShell`: **true**
   - `timeout`: **5000**
2. This only kills the process on port 8080 **if** its command line contains **UefaMatchesApplication** (so other apps on 8080 are left running). Exit code 0 means the matching process was stopped or nothing was running.

---

## If MCP is unavailable

If **user-jetbrains** or a tool is unavailable, say that the IntelliJ MCP is not connected and the user should check Cursor MCP settings and IntelliJ **Settings → Tools → MCP Server**, then retry.

## Notes

- Run configuration name: **UefaMatchesApplication** (Spring Boot).
- IntelliJ MCP server in Cursor: **user-jetbrains**.
- App default port: **8080**. Stop command only kills a process on 8080 when its command line contains **UefaMatchesApplication**, so other apps on that port are not stopped.
