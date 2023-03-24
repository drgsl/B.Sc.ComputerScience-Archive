package smartCity.service;

import org.springframework.stereotype.Service;

import javax.mail.*;
import javax.mail.internet.*;
import java.io.IOException;
import java.util.Date;
import java.util.Properties;

@Service
public class Mail {

    public Mail(){}

    public void sendmail(String receiver) throws AddressException, MessagingException, IOException {
        Properties props = new Properties();
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.starttls.enable", "true");
        props.put("mail.smtp.host", "smtp.gmail.com");
        props.put("mail.smtp.port", "587");

        Session session = Session.getInstance(props, new javax.mail.Authenticator() {
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication("smart.city.ProgAvansata@gmail.com", "pfcmwekxrktlnzyo");
            }
        });
        Message msg = new MimeMessage(session);
        msg.setFrom(new InternetAddress("pfcmwekxrktlnzyo", false));

        msg.setRecipients(Message.RecipientType.TO, InternetAddress.parse(receiver));
        msg.setSubject("Smart City email");
        msg.setContent("Smart City Reservation", "text/html");
        msg.setSentDate(new Date());

        MimeBodyPart messageBodyPart = new MimeBodyPart();
        messageBodyPart.setContent("Hello, your parking spot reservation is about to expire!", "text/html");
        Multipart multipart = new MimeMultipart();
        multipart.addBodyPart(messageBodyPart);
        /*
        MimeBodyPart attachPart = new MimeBodyPart();
        attachPart.attachFile("src/main/resources/subiecte3.png");
        multipart.addBodyPart(attachPart);
         */
        msg.setContent(multipart);
        Transport.send(msg);
    }
}