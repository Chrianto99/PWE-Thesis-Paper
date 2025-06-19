package Graph;

import java.util.*;

import Helpers.VectorOperator;
import Node.*;
import Propagation.RadiationHandler;
import Propagation.Ray;
import RoomGeometry.Room;
import RoomGeometry.RoomHandler;
import Router.*;

public class Graph {

    public List<Edge> allEdges = new ArrayList<>();
    public List<Node> allNodes = new ArrayList<>();
    public List<Ray> inputRays = new ArrayList<>();
    public TxConfig txConfig;
    public TileConfig tileConfig;
    public Room room;

    transient public int numberOfModes = 20;
    transient public Random rand;
    transient public boolean graphCreationAborted = false;


    public Graph(Room room, TxConfig txConfig, TileConfig tileConfig) {

        this.room = room;
        this.txConfig = txConfig;
        this.tileConfig = tileConfig;
        rand = new Random(System.currentTimeMillis());

        // Step 1: Randomly position SDMs (Tiles) on room walls. Position transmitter and users on random positions
        // inside the room. Finally, save all elements as nodes in allNodes list.
        NodeHandler nodeHandler = new NodeHandler(this);
        nodeHandler.initializeNodes();

        // Step 2: Create all the legal Edges and save them in allEdges list
        EdgeHandler edgeHandler = new EdgeHandler(this);
        edgeHandler.initializeEdges();

        // Step 3: Create input rays from the transmitter and save the in inputRays list.
        // Also removes edges that will not be used in the simulation
        RadiationHandler radiationHandler = new RadiationHandler(this);
        boolean transmitterBlocked = radiationHandler.createInputRays();
        if (transmitterBlocked) {
            graphCreationAborted = true;
            System.out.println("Transmitter Blocked. Graph Creation Aborted");
            return;
        }

        // Step 4: Simulate EM functions and save them in routingTable list
        // Access output distribution given node,mode and input Edge with
        // key = node.rTableIndex + edge.rTableKey * node.numModes + modeId
        ModeHandler modeHandler = new ModeHandler(this);
        boolean tileBlocked = modeHandler.initializeRoutingTables();
        if (tileBlocked) {
            graphCreationAborted = true;
            System.out.println("Tile Blocked. Graph Creation Aborted");

        }


    }

    public boolean areOnSameWall(Node node1, Node node2) {

        if (node1 instanceof Tile tile1 && node2 instanceof Tile tile2) {
            return VectorOperator.codirectional(tile1.getN(), tile2.getN());
        }

        return false;

    }

    public ArrayList<Tile> getTiles() {
        ArrayList<Tile> list = new ArrayList<>();
        for (Node node : allNodes) {
            if (node.getType().equals("Tile")) {
                list.add((Tile) node);
            }
        }
        return list;
    }

    public ArrayList<Node> getReceivers() {
        ArrayList<Node> list = new ArrayList<>();
        for (Node node : allNodes) {
            if (node.getType().equals("Rx")) {
                list.add(node);
            }
        }
        return list;
    }

    public Node getTx() {
        for (Node node : allNodes) {
            if (node.getType().equals("Tx")) return node;
        }
        return null;
    }


}
	


	
			
	



		
	
	





