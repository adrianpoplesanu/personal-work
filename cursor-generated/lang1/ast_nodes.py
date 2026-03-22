from dataclasses import dataclass, field
from typing import List, Optional


class Node:
    pass


class Expression(Node):
    pass


class Statement(Node):
    pass


@dataclass
class Program(Node):
    statements: List[Statement] = field(default_factory=list)


@dataclass
class Identifier(Expression):
    value: str = ""


@dataclass
class IntegerLiteral(Expression):
    value: int = 0


@dataclass
class StringLiteral(Expression):
    value: str = ""


@dataclass
class BooleanLiteral(Expression):
    value: bool = False


@dataclass
class PrefixExpression(Expression):
    operator: str = ""
    right: Optional[Expression] = None


@dataclass
class InfixExpression(Expression):
    left: Optional[Expression] = None
    operator: str = ""
    right: Optional[Expression] = None


@dataclass
class IfExpression(Expression):
    condition: Optional[Expression] = None
    consequence: Optional["BlockStatement"] = None
    alternative: Optional["BlockStatement"] = None


@dataclass
class FunctionLiteral(Expression):
    parameters: List[Identifier] = field(default_factory=list)
    body: Optional["BlockStatement"] = None


@dataclass
class CallExpression(Expression):
    function: Optional[Expression] = None  # Identifier or FunctionLiteral
    arguments: List[Expression] = field(default_factory=list)


@dataclass
class ArrayLiteral(Expression):
    elements: List[Expression] = field(default_factory=list)


@dataclass
class IndexExpression(Expression):
    left: Optional[Expression] = None
    index: Optional[Expression] = None


@dataclass
class LetStatement(Statement):
    name: Optional[Identifier] = None
    value: Optional[Expression] = None


@dataclass
class ReturnStatement(Statement):
    return_value: Optional[Expression] = None


@dataclass
class ExpressionStatement(Statement):
    expression: Optional[Expression] = None


@dataclass
class BlockStatement(Statement):
    statements: List[Statement] = field(default_factory=list)


@dataclass
class ThisExpression(Expression):
    pass


@dataclass
class MemberExpression(Expression):
    object: Optional[Expression] = None
    property: Optional[Identifier] = None


@dataclass
class NewExpression(Expression):
    class_name: Optional[Expression] = None
    arguments: List[Expression] = field(default_factory=list)


@dataclass
class MethodDef(Node):
    name: Optional[Identifier] = None
    parameters: List[Identifier] = field(default_factory=list)
    body: Optional[BlockStatement] = None


@dataclass
class ClassStatement(Statement):
    name: Optional[Identifier] = None
    methods: List[MethodDef] = field(default_factory=list)


@dataclass
class AssignStatement(Statement):
    target: Optional[MemberExpression] = None
    value: Optional[Expression] = None
