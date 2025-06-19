package Helpers;

import java.io.FileWriter;
import java.io.IOException;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import Graph.Graph;

public class JsonFileManager {


	
	public void writeGraphToJson(Graph g,String name) {
		
		Gson gson = new GsonBuilder().setPrettyPrinting().create();
		String json = " ";
		
		json = gson.toJson(g);
		
		       
        // Write JSON to file
        try (FileWriter writer = new FileWriter( name +".json")) {
            writer.write(json);
            System.out.println("JSON written to output.json successfully!");
        } catch (IOException e) {
            e.printStackTrace();
        }
	}



}
