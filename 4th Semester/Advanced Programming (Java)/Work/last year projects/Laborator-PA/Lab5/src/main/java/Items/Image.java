package Items;

import Exceptions.CustomException;

public class Image extends Item {

    private final boolean isLicenced;

    public Image(String path, String name, boolean isLicenced) throws CustomException {
        super(path, name);
        this.isLicenced = isLicenced;
    }

    public boolean isLicenced() {
        return isLicenced;
    }

    @Override
    public String toString() {
        return "Image with id [" + id + "] and name " + name + ". It is " + (isLicenced ? "licenced." : "not licenced.");
    }
}
