package Node;

import java.util.ArrayList;
import java.util.Hashtable;

import Graph.Edge;

public class Node {

    protected int id;
    protected String type;
    private double[] position;
    private boolean blocked;
    private Hashtable<String,double[]> routingTable;
    private int numberOfModes;

    protected transient ArrayList<Edge> inputEdges;
    protected transient ArrayList<Edge> outputEdges;

    public Node() {

    }

    public Node(String type) {
        this.type = type;
        inputEdges = new ArrayList<>();
        outputEdges = new ArrayList<>();
        routingTable = new Hashtable<>();

    }

    public void setBlocked(){
        blocked = true;
    }

    public void addKvpToRoutingTable(String key, double[] dist){

        routingTable.put(key,dist);

    }

    public int getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getType() {
        return type;
    }

    public void setPosition(double[] position) {
        this.position = position;

    }

    public double[] getPosition() {
        return position;
    }

    public void setNumberOfModes(int numberOfModes) {
        this.numberOfModes = numberOfModes;
    }

//    public void setrTableIndex(int rTableIndex) {
//        this.rTableIndex = rTableIndex;
//    }

    public ArrayList<Edge> getInputEdges() {
        return inputEdges;
    }

    public ArrayList<Edge> getOutputEdges() {
        return outputEdges;
    }

    public void addToInputEdges(Edge edge){inputEdges.add(edge);}

    public void addToOutputEdges(Edge edge){outputEdges.add(edge);}


}



