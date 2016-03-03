import java.io.*;
import java.util.HashSet;
import java.util.Scanner;

public class SplitStringIntoWords {
	
	public HashSet<String> dictionary;
	public SplitStringIntoWords() {
		dictionary = new HashSet<String>();
	}

	//Recursive Solution
	public String recursiveSolution(String inString, int start, HashSet<String> memo) {
		String buff = "";
		
		for(int i = start; i < inString.length(); i++) {
			buff = buff + inString.charAt(i);

			if(!memo.contains(i) && dictionary.contains(buff)) {		//If this split hasn't returned null before and inDictionary=true

				String result = recursiveSolution(inString,i+1,memo);
				
				if(result != null) {
					return buff + " " + result;
				}
			}
			
		}
		
		if(dictionary.contains(buff)) {
			return buff;
		}
		
		memo.add(inString.substring(start));	//Memoization. Saves all splits that eventually return null
		return null;
	}

	public String iterativeSolution(String inString) {
		int strLength = inString.length();
		int[][] table = new int[strLength][strLength];
		
		for(int i = 0; i < strLength; i++) {
			for(int j = 0; j < strLength; j++) {
				table[i][j] = -1;	//Initially set all values to false
			}
		}
		

		for(int l = 1; l <= strLength; l++) {
			for(int i = 0; i < strLength - l + 1; i++) {
				int j = i + l - 1;	//Substring from i to j of length l is being evaluated
				
				if(dictionary.contains(inString.substring(i, j+1))) {

					table[i][j] = i;	//In this case, no split is needed. Positive integers for table[][] means true.
				}
				else {		//Iterate through substring to see if there is a split possible
					
					for(int k = i+1; k <= j; k++) {
						if(table[i][k-1] != -1 && table[k][j] != -1) {
							table[i][j] = k;
							break;		//finds first substring in dictionary
						}
					}
					
				}
			}
		}
		if(table[0][strLength-1] == -1) {
			return null;
		}
		
		StringBuffer solution = new StringBuffer();
		int i = 0;
		int j = strLength-1;
		//create final string from inString and table k's
		while(i < j) {
			int k = table[i][j];
			if(i == k) {
				solution.append(inString.substring(i, j+1));
				break;
			}
			solution.append(inString.substring(i, k) + " ");
			i = k;
		}
		
		return solution.toString();
	}
	
	/*
	 * General helper functions
	 */
	
	// Loads dictionary file into hashset
	public void uploadDictionary() {
		String fileName = "diction10k.txt";
		String line = "";		
		try {
			File file = new File(fileName);
			Scanner scanner = new Scanner(file);
			while(scanner.hasNextLine()) {
				line = scanner.nextLine();
				dictionary.add(line);
			}
			scanner.close();
		}
		catch(Exception ex) {
            System.out.println("Exception: " + ex.toString());
            System.exit(1);
        }
	}
	
	
	//Prints result
	public void printResult(String s) {
		if(s != null) {
			System.out.println("YES, it can be split");
			System.out.println(s);
			System.out.println();
		}
		else {
			System.out.println("No, cannot be split.");
			System.out.println();
		}
	}
	
	//Main
	public static void main(String[] args) {
		
		SplitStringIntoWords ssiw = new SplitStringIntoWords();	
		ssiw.uploadDictionary();
		Scanner in = new Scanner(System.in);
		int numOfLines = Integer.parseInt(in.nextLine());
		
		for(int i = 0; i < numOfLines; i++) {
			System.out.println("Phase number: " + (i+1));
			String line = in.nextLine();
			System.out.println(line + '\n');
			
			System.out.println("Iterative Attempt:");
			String result1 = ssiw.iterativeSolution(line);
			ssiw.printResult(result1);
			
			System.out.println("Recursive Attempt:");
			String result2 = ssiw.recursiveSolution(line, 0, new HashSet<String>());
			ssiw.printResult(result2);
		}
			
		in.close();
	}

}
