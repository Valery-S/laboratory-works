using MySite.Models;
using System.Linq;

namespace MySite
{
	public class InitalData
	{
		public static void Initialize(PictureContext context)
		{
			if (!context.Pictures.Any())
			{
				context.Pictures.AddRange(
					new Picture
					{
						Name = "3.jpg",
						Likes = 0,
						Dislikes = 0,
						Grade = 0
					},
					new Picture
					{
						Name = "4.jpg",
						Likes = 0,
						Dislikes = 0,
						Grade=0
					}
					);
				context.SaveChanges();
			}
		}
	}
}
