package laborator11.clientapplication;

import com.github.javafaker.Faker;
import laborator11.clientapplication.model.User;
import netscape.javascript.JSObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.configurationprocessor.json.JSONException;
import org.springframework.boot.configurationprocessor.json.JSONObject;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.http.*;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.client.RestTemplate;

import java.util.List;


@RestController
public class CallService {

    final Logger log = LoggerFactory.getLogger(CallService.class);
    final String uri = "http://localhost:8081";

    @GetMapping("/call")
    public List<User> getUsers() {
        String uriGet = uri + "/users";
        log.info("Start");
        RestTemplate restTemplate = new RestTemplate();
        ResponseEntity<List<User>> response = restTemplate.exchange(
                uriGet, HttpMethod.GET, null,
                new ParameterizedTypeReference<List<User>>() {
                });
        List<User> result = response.getBody();
        result.forEach(p -> log.info(p.toString()));
        log.info("Stop");
        return result;
    }

    @PostMapping(value = "/invoke")
    ResponseEntity<String> addUser() throws JSONException {
        String uriPost = uri + "/users";
        Faker faker = new Faker();
        String name = faker.artist().name();
        log.info("Start");

        RestTemplate restTemplate = new RestTemplate();
        JSONObject request = new JSONObject();
        request.put("name", name);

        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);
        HttpEntity<String> entity = new HttpEntity<String>(request.toString(), headers);

        ResponseEntity<String> loginResponse = restTemplate
                .exchange(uriPost, HttpMethod.POST, entity, String.class);

        return new ResponseEntity<>("User added successfully\n", HttpStatus.CREATED);
    }

}
