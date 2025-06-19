package Propagation;

import Graph.Edge;

import java.util.ArrayList;

public class Ray {

    private double power;
    private double length;
    private int currentNode_id;
    private ArrayList<Integer> edges;


    public Ray(double totalPower, Edge edge, int nodeId) {

        this.power = totalPower;
        this.length = edge.getLength();
        this.currentNode_id = nodeId;
        edges = new ArrayList<>();
        edges.add(edge.getId());


    }





}
