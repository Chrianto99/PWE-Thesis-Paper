package RoomGeometry;

import Helpers.VectorOperator;

import java.util.Random;

public class RoomHandler {

    private Room room;
    private Random rand;
    private static int MAX_NUM_SPHERES = 10;
    private static double MAX_SPHERE_RADIUS;

    public RoomHandler() {
        room = new Room();
        rand = new Random(System.currentTimeMillis());
    }

    public RoomHandler(Room room) {
        this.room = room;
        rand = new Random();

    }


    public void createCuboidRoom(double[] roomDims) {
        double roomX = roomDims[0], roomY = roomDims[1], roomZ = roomDims[2];
        room.setDims(roomDims);
        double totalArea = 0;

        // Left wall (x = 0)
        Surface left = new Surface();
        left.initializeSurfaceYZ(new double[]{0, roomY}, new double[]{0, roomZ}, 0);
        totalArea += left.getArea();
        room.addToSurfaces(left);

        // Right wall (x = roomX)
        Surface right = new Surface();
        right.initializeSurfaceYZ(new double[]{0, roomY}, new double[]{0, roomZ}, roomX);
        totalArea += right.getArea();
        VectorOperator.reverseVector(right.getN());
        room.addToSurfaces(right);

        // Back wall (y = 0)
        Surface back = new Surface();
        back.initializeSurfaceXZ(new double[]{0, roomX}, new double[]{0, roomZ}, 0);
        totalArea += back.getArea();
        room.addToSurfaces(back);

        // Front wall (y = roomY)
        Surface front = new Surface();
        front.initializeSurfaceXZ(new double[]{0, roomX}, new double[]{0, roomZ}, roomY);
        totalArea += front.getArea();
        VectorOperator.reverseVector(front.getN());
        room.addToSurfaces(front);

        // Ceiling (z = roomZ)
        Surface ceiling = new Surface();
        ceiling.initializeSurfaceXY(new double[]{0, roomX}, new double[]{0, roomY}, roomZ);
        totalArea += ceiling.getArea();
        VectorOperator.reverseVector(ceiling.getN());
        room.addToSurfaces(ceiling);

        room.setTotalArea(totalArea);

    }

    public void addSpheres(int numSpheres) {
        double roomX = room.getDims()[0], roomY = room.getDims()[1], roomZ = room.getDims()[2];
        MAX_SPHERE_RADIUS = Math.sqrt(roomX * roomX + roomY * roomY + roomZ * roomZ) / 5;

        for (int i = 0; i < numSpheres; i++) {

            double[] position = new double[]{rand.nextDouble(roomX), rand.nextDouble(roomY), rand.nextDouble(roomZ)};
            double radius = rand.nextDouble(MAX_SPHERE_RADIUS);

            room.addToObstacles(new Sphere(position, radius));

        }

    }

    public Room getRoom() {
        return room;
    }


}
