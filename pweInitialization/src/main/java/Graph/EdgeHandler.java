package Graph;

import Helpers.VectorOperator;
import Node.*;
import RoomGeometry.Obstacle;
import RoomGeometry.Sphere;

import java.util.List;

public class EdgeHandler {

    Graph g;
    int edgeId = 0;


    public EdgeHandler(Graph g) {
        this.g = g;
    }

    public void initializeEdges() {

        List<Tile> tiles = g.getTiles();
        // Creates edges between tiles that are not on same wall
        createEdgesBetweenTiles(tiles);
        // Creates edges between tiles and receivers
        createReceiverEdges(tiles);
        // Creates edges between tiles and transmitter
        createTransmitterEdges(tiles);


    }

    public void createEdgesBetweenTiles(List<Tile> tiles) {

        for (Tile startTile : tiles) {
            for (Tile destTile : tiles) {

                boolean areOnSameWall = g.areOnSameWall(startTile, destTile);
                boolean edgeBlockedByObstacle = edgeBlocked(startTile.getPosition(), destTile.getPosition());

                if (!areOnSameWall && !edgeBlockedByObstacle) {
                    createEdge(startTile, destTile);

                }
            }
        }
    }

    public void createReceiverEdges(List<Tile> tiles) {

        List<Node> receivers = g.getReceivers();
        for (Tile tile : tiles) {

            for (Node receiver : receivers) {

                boolean edgeBlockedByObstacle = edgeBlocked(tile.getPosition(), receiver.getPosition());

                if (!edgeBlockedByObstacle) {
                    createEdge(tile, receiver);
                }

            }

        }
    }

    public void createTransmitterEdges(List<Tile> tiles) {

        Node transmitter = g.getTx();
        for (Tile tile : tiles) {

            boolean edgeBlockedByObstacle = edgeBlocked(transmitter.getPosition(), tile.getPosition());

            if (!edgeBlockedByObstacle) {
                createEdge(transmitter, tile);
            }

        }
    }


    public void createEdge(Node startNode, Node destNode) {

        double length = VectorOperator.distance(startNode.getPosition(), destNode.getPosition());
        Edge newEdge = new Edge(startNode, destNode, edgeId++, length);
        newEdge.setVector(VectorOperator.calculateVector(startNode.getPosition(), destNode.getPosition()));
        calculatePathLoss(newEdge, startNode); // Precalculate Path Loss only for product of Distances

        g.allEdges.add(newEdge);
        startNode.addToOutputEdges(newEdge);
        destNode.addToInputEdges(newEdge);

    }

    public boolean edgeBlocked(double[] point1, double[] point2) {
        for (Obstacle obst : g.room.getObstacles()) {
            Sphere sphere = (Sphere) obst;
            if (VectorOperator.segmentIntersectsSphere(point1, point2, sphere.getCenter(), sphere.getRadius()))
                return true;
        }

        return false;

    }


    public void calculatePathLoss(Edge newEdge, Node start) {
        double Gt = g.txConfig.getGain();
        double wavelength = g.txConfig.getWavelength();
        double Gtile = g.tileConfig.getMaxGain();
        double alpha = g.room.getAlpha();
        double edgeLength = newEdge.getLength();

        double v = (4 * Math.PI / wavelength) * (4 * Math.PI / wavelength) * Math.pow(edgeLength, alpha);

        if (start.getType().equals("Tx"))
            newEdge.setPathLoss((Gt / v));
        else
            newEdge.setPathLoss(Gtile / v);

    }


}
