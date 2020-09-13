package clustering;

import YASS.DistanceMeasure;

import java.util.List;
import java.util.concurrent.RecursiveTask;

public class ClusterDistanceTask extends RecursiveTask<Float> {

	private static long SEQUENTIAL_THRESHOLD = 5000;
	
	public static float calculateClusterDistance(Cluster c1, Cluster c2, DistanceMeasure d) {
		int n1 = c1.getWords().size();
		int n2 = c2.getWords().size();
		long last = n1 * n2;
		int cores = Runtime.getRuntime().availableProcessors();
		SEQUENTIAL_THRESHOLD = (long)Math.ceil((double) last / (4.0 * cores));
		return ClusterManager.commonPool.invoke(new ClusterDistanceTask(c1, c2, d, 0, last));
	}
	
	private Cluster c1;
	private Cluster c2;
	private long start;
	private long end;
	private DistanceMeasure d;
	private int n2;
	
	private ClusterDistanceTask(Cluster c1, Cluster c2, DistanceMeasure d, long start, long end) {
		this.c1 = c1;
		this.c2 = c2;
		this.start = start;
		this.end = end;
		this.d = d;
		this.n2 = c2.getWords().size();
	}
	
	private int _i(long k) {
		return (int)(k / n2);
	}
	
	private int _j(long k) {
		return (int)(k % n2);
	}
	
	@Override
	protected Float compute() {
		if (end - start <= SEQUENTIAL_THRESHOLD) {
			float maxDist = 0;
			
			List<String> words1 = c1.getWords();
			List<String> words2 = c2.getWords();
			for (long k = start; k < end; k++) {
				int i = _i(k);
				int j = _j(k);
				float distance = d.calculate(words1.get(i), words2.get(j));
				if (distance > maxDist) {
					maxDist = distance;
				}
			}
			return maxDist;
		} else {
			long mid = start + (end - start) / 2;
			ClusterDistanceTask left = new ClusterDistanceTask(c1, c2, d, start, mid);
			ClusterDistanceTask right = new ClusterDistanceTask(c1, c2, d, mid, end);
			left.fork();
			float rightAns = right.compute();
			float leftAns = left.join();
			return Math.max(rightAns, leftAns);
		}
	}
	

}
