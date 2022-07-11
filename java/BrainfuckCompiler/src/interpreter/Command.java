package interpreter;

public class Command {
    private CommandType type;
    private int matchingBracket;

    public Command(CommandType type, int matchingBracket) {
        this.type = type;
        this.matchingBracket = matchingBracket;
    }

    public CommandType getType() {
        return type;
    }

    public void setType(CommandType type) {
        this.type = type;
    }

    public int getMatchingBracket() {
        return matchingBracket;
    }

    public void setMatchingBracket(int matchingBracket) {
        this.matchingBracket = matchingBracket;
    }
}
