using Microsoft.AspNetCore.Mvc;
using MySite.Models;
using System.Linq;

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
      return View(db.Pictures.ToList());
    }

  }
}
