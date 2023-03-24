package database.entities;

import java.sql.Date;
import java.util.Objects;

public class Movie {
    private int id;
    private String title;
    private Date release_date;
    private int duration;
    private int score;

    public Movie() {}

    public Movie(int id, String title, Date release_date, int duration, int score) {
        this.id = id;
        this.title = title;
        this.release_date = release_date;
        this.duration = duration;
        this.score = score;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    @Override
    public String toString() {
        return "Movie: " +
                " [ID] " + id +
                " [TITLE]" + title +
                " [RELEASE DATE] " + release_date +
                " [DURATION] " + duration +
                " [SCORE] " + score;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public Date getRelease_date() {
        return release_date;
    }

    public void setRelease_date(Date release_date) {
        this.release_date = release_date;
    }

    public int getDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Movie movie = (Movie) o;
        return id == movie.getId() && duration == movie.getDuration() && score == movie.getScore() && title.equals(movie.getTitle());
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, title, release_date, duration, score);
    }
}
