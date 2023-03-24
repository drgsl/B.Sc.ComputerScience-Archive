package com.example.lab11.entity;

import javax.persistence.*;

@Entity
@Table(name = "message")
public class Message {

    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long idSender;
    private Long idReceiver;
    private String message;

    public Message(Long idSender, Long idReceiver, String message) {
        this.idSender = idSender;
        this.idReceiver = idReceiver;
        this.message = message;
    }

    public Message() {

    }

    public Long getIdSender() {
        return idSender;
    }

    public void setIdSender(Long idSender) {
        this.idSender = idSender;
    }

    public Long getIdReceiver() {
        return idReceiver;
    }

    public void setIdReceiver(Long idReceiver) {
        this.idReceiver = idReceiver;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public void setId(Long id) {
        this.id = id;
    }

    @Id
    public Long getId() {
        return id;
    }
}
