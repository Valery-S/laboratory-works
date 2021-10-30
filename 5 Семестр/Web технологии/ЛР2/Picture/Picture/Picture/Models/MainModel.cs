using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Picture.Models
{
	public class MainModel
	{
		public List<PictureModel> Pictures;
		public int Count;

		public MainModel(int c, List<PictureModel> p)
		{
			Pictures = p;
			Count = c;
		}
	}
}
