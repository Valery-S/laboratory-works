using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Picture.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;

namespace Online_shop.Controllers
{
	public class HomeController : Controller
	{
		private readonly ILogger<HomeController> _logger;

		public HomeController(ILogger<HomeController> logger)
		{
			_logger = logger;
		}

		public IActionResult Index()
		{

			return View();
		}

		public IActionResult Like_or_dislike()
		{
			return View();
		}
		public IActionResult Delete_or_add()
		{
			return View();
		}

	}
}
