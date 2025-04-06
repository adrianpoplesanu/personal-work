class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        for c in s:
            if c == '(':
                stack.append(c)
            if c == '{':
                stack.append(c)
            if c == '[':
                stack.append(c)
            if c == ')':
                if len(stack) == 0 or stack[-1] != '(':
                    return False
                stack.pop()
            if c == '}':
                if len(stack) == 0 or stack[-1] != '{':
                    return False
                stack.pop()
            if c == ']':
                if len(stack) == 0 or stack[-1] != '[':
                    return False
                stack.pop()
        if len(stack) > 0:
            return False
        return True

solution = Solution()
print(solution.isValid('()[]{}'))
