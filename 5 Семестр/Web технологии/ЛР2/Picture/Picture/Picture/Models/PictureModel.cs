using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Picture.Models{
	public class PictureModel{
		public int Number { get; set; }
		public int Likes { get; set; }
		public int Dislike { get; set; }

		public PictureModel(int n, int l, int dl)
		{
			Number = n;
			Likes = l;
			Dislike = dl;
		}

	}
}
