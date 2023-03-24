package com.company;

public class CommandException extends Exception {
    String message;
    String messageInDepth;

    public CommandException(String message) {
        this.message = message;
        this.messageInDepth = message + " -- \n"
                + "Localized message : " + this.getLocalizedMessage();
    }

    @Override
    public String getMessage() {
        return message;
    }

    public String getMessageInDepth() {
        return messageInDepth;
    }
}
