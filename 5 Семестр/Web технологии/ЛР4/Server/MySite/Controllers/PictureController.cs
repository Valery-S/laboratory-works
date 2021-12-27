using Microsoft.AspNetCore.Mvc;
using MySite.Models;

using System.Linq;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace MySite.Controllers
{
	[ApiController]
	[Route("[controller]")]
	public class PictureController : Controller
	{
		PictureContext db;

		public PictureController(PictureContext context)
		{
			db = context;
		}
		[HttpGet]
		public IEnumerable<Picture> Get()
		{
			return db.Pictures.ToList();
		}

		[HttpPost]
		public void PostPicture(Picture product)
		{
			db.Pictures.Add(product);
			db.SaveChanges();
		}

		[HttpPut]
		public void PutPicture(Picture product)
		{
			db.Pictures.Update(product);
			db.SaveChanges();
		}

		[HttpDelete("{id}")]
		public void DeletePicture(int id)
		{
			foreach (var product in db.Pictures.ToList())
			{
				if (product.Id == id) db.Pictures.Remove(product);
			}
			db.SaveChanges();
		}

	}
}
