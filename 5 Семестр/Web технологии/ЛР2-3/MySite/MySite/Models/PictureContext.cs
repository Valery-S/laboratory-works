using Microsoft.EntityFrameworkCore;

namespace MySite.Models
{
	public class PictureContext : DbContext
  {
    public DbSet<Picture> Pictures { get; set; }

    public PictureContext(DbContextOptions<PictureContext> options)
        : base(options)
    {
      Database.EnsureCreated();
    }
  }
}
