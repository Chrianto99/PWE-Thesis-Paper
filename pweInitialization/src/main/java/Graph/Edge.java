package Graph;

import Node.*;

public class Edge {

    private int id;
    private int startNode_id;
    private int destNode_id;
    private double length;
    private double pathLoss;
    private double[] vector;
    private transient Node startNode;
    private transient Node destNode;


    public Edge(Node start, Node end, int idx, double length) {
        this.startNode = start;
        this.destNode = end;
        this.id = idx;
        this.length = length;
        this.startNode_id = start.getId();
        this.destNode_id = end.getId();
        vector = new double[3];


    }

    public int getId() {
        return id;
    }

    public int getDestNode_id() {
        return destNode_id;
    }

    public double getLength() {
        return length;
    }

    public double getPathLoss() {
        return pathLoss;
    }

    public void setPathLoss(double pathLoss) {
        this.pathLoss = pathLoss;
    }

    public double[] getVector() {
        return vector;
    }

    public void setVector(double[] vector) {
        this.vector = vector;
    }




}
