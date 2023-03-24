package OptionalClasses;

import CatalogUtilities.Catalog;
import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

import java.io.*;

public class ReportCommand extends Command {
    public ReportCommand(Catalog catalog) {
        super(catalog);
        callMethod = "report";
    }

    @Override
    public void execute(String arguments) throws IOException
    {
        try
        {
            Configuration cfg = new Configuration(Configuration.VERSION_2_3_29);
            cfg.setDirectoryForTemplateLoading(new File("./"));

            Template temp = cfg.getTemplate("templateFile.ftlh");
            Writer out = new OutputStreamWriter(new FileOutputStream("templateFile.html"));
            temp.process(catalog, out);
        }
        catch (TemplateException e)
        {
            System.out.println(e.getMessage());
        }
    }
}
