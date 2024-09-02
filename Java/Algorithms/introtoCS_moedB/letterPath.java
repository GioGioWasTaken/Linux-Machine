class letterPath{
	public static void main(String[] args) {
		
	}
	public static int lengthPath (char[][] mat, String pattern){
		return lengthPath(mat,pattern, 0,0);
	}

	public static int lengthPath (char[][] mat, String pattern, int row, int col){
		if(row == mat.length || col == mat[0].length){
			return 0;
		}
	}
}
