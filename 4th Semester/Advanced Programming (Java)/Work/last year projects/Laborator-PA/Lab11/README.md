For the compulsory part, I have done the following:
<ul>
    <li>added a PersonEntity class describing the 'persons' table in the database</li>
    <li>added a PersonRelationshipsEntity class describing the 'relationships' table in the database</li>
    <li>added a PersonService class that interacts with the PersonRepository (JpaRepository)</li>
    <li>added a PersonController class that handles the requests (GET, POST, PUT and DELETE) at the associated links</li>
    <li>added settings in the application.properties file to enable a local connection to the database</li>
    <li>tested the implementation using Postman (local testing at the following link: <a>http://localhost:8081/person/</a></li>
</ul>