package Helpers;

public class VectorOperator {



    public static double[] calculateVector(double[] p1, double[] p2) {

        double Vx, Vy, Vz;
        Vx = p2[0] - p1[0];
        Vy = p2[1] - p1[1];
        Vz = p2[2] - p1[2];


        return new double[]{Vx, Vy, Vz};

    }

    public static double distance(double[] p1, double[] p2) {

        double dx = Math.pow((p2[0] - p1[0]), 2);
        double dy = Math.pow((p2[1] - p1[1]), 2);
        double dz = Math.pow((p2[2] - p1[2]), 2);

        return Math.sqrt(dx + dy + dz);
    }

    public static double squaredDistance(double[] p1, double[] p2) {

        double dx = Math.pow((p2[0] - p1[0]), 2);
        double dy = Math.pow((p2[1] - p1[1]), 2);
        double dz = Math.pow((p2[2] - p1[2]), 2);

        return dx + dy + dz;
    }

    public static double[] projectOntoPlane(double[] ve, double[] n) {
        double dotProduct = dotProduct(ve, n);
        return new double[]{
                ve[0] - dotProduct * n[0],
                ve[1] - dotProduct * n[1],
                ve[2] - dotProduct * n[2]
        };
    }

    public static double calculatePhiAngle(double[] n, double[] v, double[] u, double[] ve) {
        double[] V_proj = projectOntoPlane(ve, n);
        double dotV = dotProduct(V_proj, v);
        double dotU = dotProduct(V_proj, u);

        return Math.atan2(dotV, dotU); // Phi in radians
    }

    public static double calculateAngle(double[] v1, double[] v2) {
        double dotProduct = dotProduct(v1, v2);
        double magnitudeV1 = magnitude(v1);
        double magnitudeV2 = magnitude(v2);

        double value = dotProduct / (magnitudeV1 * magnitudeV2);

        // Clamp value to prevent NaN from acos()
        value = Math.max(-1.0, Math.min(1.0, value));

        return Math.acos(value);

    }

    public static boolean segmentIntersectsSphere(double[] P1, double[] P2, double[] sphereCenter, double sphereRadius) {
        // Direction vector of the segment
        double[] V = {P2[0] - P1[0], P2[1] - P1[1], P2[2] - P1[2]};

        // Vector from P1 to the sphere center
        double[] L = {sphereCenter[0] - P1[0], sphereCenter[1] - P1[1], sphereCenter[2] - P1[2]};

        // Project L onto V to find the closest point on the infinite line
        double t = dotProduct(L, V) / dotProduct(V, V);

        // Clamp t to the segment's range [0,1]
        t = Math.max(0, Math.min(1, t));

        // Compute the closest point on the segment
        double[] closestPoint = {
                P1[0] + t * V[0],
                P1[1] + t * V[1],
                P1[2] + t * V[2]
        };

        // Compute squared distance from closest point to sphere center
        double distanceSquared = squaredDistance(closestPoint, sphereCenter);

        // Check if the distance is within the sphere's radius
        return distanceSquared <= sphereRadius * sphereRadius;
    }
    public static double[] getPerpendicularVector(double[] normal) {
        // Step 1: Choose an arbitrary vector that is not parallel to the normal
        double[] arbitrary = Math.abs(normal[0]) < 0.99 ? new double[]{1, 0, 0} : new double[]{0, 1, 0};

        // Step 2: Compute a perpendicular vector using the cross product
        double[] perpendicular = crossProduct(normal, arbitrary);

        // Step 3: Normalize the perpendicular vector
        normalize(perpendicular);

        return perpendicular;
    }

    public static boolean codirectional(double[] v1, double[] v2) {
        return calculateAngle(v1, v2) == 0;
    }

    public static void reverseVector(double[] vector) {

        for (int i = 0; i < vector.length; i++) {
            vector[i] *= -1;
        }

    }

    public static double magnitude(double[] v) {
        return Math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    private static double[] crossProduct(double[] a, double[] b) {
        return new double[]{
                a[1] * b[2] - a[2] * b[1],
                a[2] * b[0] - a[0] * b[2],
                a[0] * b[1] - a[1] * b[0]
        };
    }

    private static void normalize(double[] vector) {
        double length = Math.sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
        if (length > 0) {
            vector[0] /= length;
            vector[1] /= length;
            vector[2] /= length;
        }
    }

    public static double dotProduct(double[] v1, double[] v2) {
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }

    public static boolean isZero(double[] v) {
        int c = 0;
        for (double value : v) {
            if (value == 0) c++;
        }
        return c == v.length;

    }

    public static void printVector(double[] v) {

        for (double value : v) {
            System.out.print(value + ",");
        }
        System.out.println();

    }


}
