/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';

/// Vendor Modules
import sharp from 'sharp';

//  PROPERTIES  //

const g_root = path.resolve(__dirname, '..', '..');
const g_outdir = path.resolve(g_root, 'dist', 'vscode', 'icons');
const g_svg = path.resolve(g_root, 'icons', 'talos.svg');
const g_png = path.resolve(g_outdir, 'talos.png');

//  TOOL RUNNER  //

(async () => {
    const buffer = await sharp(g_svg).png().resize(128, 128).toBuffer();
    if (!fs.existsSync(g_outdir)) await fs.promises.mkdir(g_outdir, { recursive: true });
    await fs.promises.writeFile(g_png, buffer); // and write the output
    await fs.promises.copyFile(g_svg, path.resolve(g_outdir, 'talos.svg'));
})();
