---
name: run-tests-intellij
description: Runs tests using the IntelliJ MCP server. Use when the user says run tests, run the tests, execute tests, run a specific test (e.g. UefaMatchesApplicationTests.testSomething), or similar. Do not use Gradle or terminal; use the JetBrains MCP (user-jetbrains).
---

# Run Tests via IntelliJ MCP

## When to apply

Apply this skill when the user asks to **run tests** (e.g. "run the tests", "run tests", "execute tests", "run UefaMatchesApplicationTests", "run UefaMatchesApplicationTests.testSomething").

## Rule

**Always run this project's tests using the IntelliJ MCP**, not `./gradlew test` or any terminal command.

## Steps

1. **Resolve the run configuration name**
   - If the user specified a test (e.g. "UefaMatchesApplicationTests.testSomething"), use that as the configuration name; IntelliJ run configs for tests are typically **`ClassName.testMethodName`** for a single test or **`ClassName`** for a whole test class.
   - If unsure, call **user-jetbrains** → **get_run_configurations** with `projectPath`: workspace root, and pick the configuration whose `name` matches the requested test or class.

2. **Run the test**
   - Call **user-jetbrains** → **execute_run_configuration** with:
     - `configurationName`: the test run configuration name (e.g. **UefaMatchesApplicationTests.testSomething** or **UefaMatchesApplicationTests**).
     - `projectPath`: workspace root.
     - `timeout`: **60000** (ms). Tests may take a while; increase if needed for full suite.

3. Report the result: exit code 0 and "BUILD SUCCESSFUL" mean tests passed; non-zero or failure output means they failed.

## If MCP is unavailable

If **user-jetbrains** or a tool is unavailable, say that the IntelliJ MCP is not connected and the user should check Cursor MCP settings and IntelliJ **Settings → Tools → MCP Server**, then retry.

## Notes

- IntelliJ MCP server in Cursor: **user-jetbrains**.
- Test run configuration names follow IntelliJ’s pattern (e.g. `UefaMatchesApplicationTests.testSomething` for a single test method).
