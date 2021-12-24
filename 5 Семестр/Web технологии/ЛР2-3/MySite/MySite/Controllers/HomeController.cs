using Microsoft.AspNetCore.Mvc;
using MySite.Models;
using System.Linq;
using System.Data.SqlClient;

namespace MySite.Controllers
{
  public class HomeController : Controller
  {
    PictureContext db;
    public HomeController(PictureContext context)
    {
      db = context;
    }
    public IActionResult Index()
    {
      var pic = from p in db.Pictures
                select p;
      pic = pic.OrderByDescending(p => p.Grade);
      return View(pic.ToList());
    }

    [HttpGet]
    public IActionResult ADD()
    {
      return View(db.Pictures.ToList());
    }

    [HttpPost]
    public IActionResult ADD(Picture pic)
    {
      db.Pictures.Add(pic);
      db.SaveChanges();
      return RedirectToAction("Index");
    }

    [HttpGet]
    public IActionResult Delete(int? id)
    {
      if (id == null) return RedirectToAction("Index");
      ViewBag.PictireID = id;
      return View(db.Pictures.ToList());
    }

    [HttpPost]
    public IActionResult Delete(Picture pic)
    {
      db.Pictures.Remove(pic);
      db.SaveChanges();
      return RedirectToAction("Index");
    }

    [HttpGet]
    public IActionResult Like_or_dislike(int? id)
    {
      if (id == null) return RedirectToAction("Index");
      ViewBag.PictireID = id;
      return View(db.Pictures.ToList());
    }
    [HttpPost]
    public RedirectResult Like_or_dislike(Picture pic,int was_liked)
    {
      int id = pic.Id;
      int next_id = 0;

      var p1 = db.Pictures.ToList();
      for (int i = 0; i <p1.Count()-1; i++)
			{
				if (p1[i].Id == id) { next_id = p1[i + 1].Id; }
			}

      int last_id = db.Pictures.ToList().LastOrDefault().Id;
      int first_id = db.Pictures.ToList().FirstOrDefault().Id;

      if (id == last_id) { next_id = first_id; }
      foreach (var p in db.Pictures.ToList())
      {
         if (p.Id == pic.Id)
         {
					if (was_liked == 1) { p.Likes++; }
          if (was_liked == 0) { p.Dislikes++; }
        }
        p.Grade = p.Likes - p.Dislikes;
         db.Pictures.Update(p);
       }
       db.SaveChanges();



      return Redirect("/Home/Like_or_dislike/" + next_id);
      }
   
  }
}
