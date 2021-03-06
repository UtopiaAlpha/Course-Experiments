package clustering;

import YASS.DistanceMeasure;

import java.util.ArrayList;
import java.util.List;

public class Cluster {
	public static Cluster merge(int id, Cluster c1, Cluster c2) {
		List<String> newWords = (ArrayList<String>)((ArrayList<String>)c1.words).clone();
		newWords.addAll(c2.words);
		return new Cluster(id, newWords);
	}
	
	public static Cluster merge2(int id, Cluster c1, Cluster c2) {
		List<String> newWords = (ArrayList<String>)((ArrayList<String>)c1.words).clone();
		List<String> temp = new ArrayList<>();
		for (String word : c2.words) {
			boolean repeated = false;
			for (String newWord : newWords) {
				if (newWord == word) {
					repeated = true;
				}
			}
			if (!repeated) temp.add(word);
		}
		newWords.addAll(temp);
		return new Cluster(id, newWords);
	}
	
	private int id;
	private List<String> words;
	private String longestPrefix;
	
	public Cluster(int id, List<String> words) {
		this.id = id;
		this.words = words;
		
		String longestWord = words.get(0);
		String shortestWord = words.get(0);
		
		for (String w : this.words){
			if (w.length() > longestWord.length()) {
				longestWord = w;
			}
			if (w.length() < shortestWord.length()) {
				shortestWord = w;
			}
		}
		
		this.longestPrefix = "";
		for (int i = 0; i < shortestWord.length(); i++) {
			Character c = shortestWord.charAt(i);
			boolean stop = false;
			for (String w : this.words) {
				if (w.charAt(i) != c) {
					stop = true;
					break;
				}
			}
			
			if (!stop) {
				this.longestPrefix = this.longestPrefix.concat(c.toString());
			} else {
				break;
			}
		}
	}
	
	public float distance(Cluster nextCluster, DistanceMeasure d) {
		if (this.words.size() == 1 && nextCluster.words.size() == 1) {
			return d.calculate(this.words.get(0), nextCluster.words.get(0));
		} else if (this.words.size() * nextCluster.words.size() < 5000) {
			float maxDist = 0;
			for (String w1 : this.words) {
				for (String w2 : nextCluster.words) {
					float dist = d.calculate(w1, w2);
					if (dist > maxDist) {
						maxDist = dist;
					}
				}
			}
			return maxDist;
		} else {
			return ClusterDistanceTask.calculateClusterDistance(this, nextCluster, d);
		}
	}
	
	public String getCentralWord() {
		return this.longestPrefix;
	}
	
	public int getId() {
		return id;
	}
	
	public List<String> getWords() {
		return words;
	}
	
}
