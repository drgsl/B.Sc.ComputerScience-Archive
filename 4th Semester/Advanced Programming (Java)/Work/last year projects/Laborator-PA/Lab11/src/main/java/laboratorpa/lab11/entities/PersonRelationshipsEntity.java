package laboratorpa.lab11.entities;



public class PersonRelationshipsEntity {

    Integer idOfPerson;

    Integer idOfFriend;

    public PersonRelationshipsEntity() {
    }

    public PersonRelationshipsEntity(Integer idOfPerson, Integer idOfFriend) {
        this.idOfPerson = idOfPerson;
        this.idOfFriend = idOfFriend;
    }

    public Integer getIdOfPerson() {
        return idOfPerson;
    }

    public void setIdOfPerson(Integer idOfPerson) {
        this.idOfPerson = idOfPerson;
    }

    public Integer getIdOfFriend() {
        return idOfFriend;
    }

    public void setIdOfFriend(Integer idOfFriend) {
        this.idOfFriend = idOfFriend;
    }
}
