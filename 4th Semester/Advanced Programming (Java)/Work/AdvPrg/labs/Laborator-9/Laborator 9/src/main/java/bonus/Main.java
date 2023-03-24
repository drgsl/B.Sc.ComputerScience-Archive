package bonus;

public class Main {
    public static void main(String[] args) {
        RepoFactory repo = new RepoFactory();
        AbstractRepository repository = repo.getRepository("City","JPA");
        System.out.println(repository.toString());
    }
}
