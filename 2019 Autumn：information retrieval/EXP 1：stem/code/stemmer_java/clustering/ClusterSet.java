package clustering;

import java.util.*;

/**
 * @author dell
 *
 */
public class ClusterSet {

	private Map<Integer, Cluster> dict;
	private float threshold;
	
	public ClusterSet(float threshold) {
		this.dict = new HashMap<>();
		this.threshold = threshold;
	}

	public float getThreshold() {
		return threshold;
	}

	public void setThreshold(float threshold) {
		this.threshold = threshold;
	}
	
	public void addCluster(Cluster cluster) {
		dict.put(cluster.getId(),  cluster);
	}
	
	public void removeCluster(int clusterId) {
		if (dict.keySet().contains(clusterId)) {
			dict.remove(clusterId);
		}
	}
	
	public Cluster getCluster(int clusterId) {
        return dict.get(clusterId);
    }

    public Set<Integer> getClustersId() {
        return dict.keySet();
    }

    public ClusterSet copy() {
        ClusterSet newCopy = new ClusterSet(threshold);

        for (Integer key : dict.keySet()) {
            Cluster newCluster = new Cluster( dict.get(key).getId(), new ArrayList<>(dict.get(key).getWords()));
            newCopy.addCluster(newCluster);
        }

        return newCopy;
    }
    
    public void print() {
    	for (Integer key : dict.keySet()) {
    		System.out.println("Cluster " + dict.get(key).getId() + ":");
    		for (String word : dict.get(key).getWords()) {
    			System.out.print(word + "\t");
    		}
    		System.out.println();
        }
    }
}
