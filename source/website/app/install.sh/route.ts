/// Node Modules
import * as fs from 'node:fs';

/// Vendor Modules
import { NextResponse } from 'next/server';

/// Website Modules
import { Assets } from '@/website/assets';

/** Ensure no caching occurs. */
export const revalidate = false;

/** Gets the "install.sh" script. */
export async function GET() {
    const body = await fs.promises.readFile(Assets.scripts('install.sh'), 'utf-8'); // prepare the incoming body
    const headers = { 'Content-Disposition': 'inline; filename="install.sh"', 'Content-Type': 'text/plain' };
    return new NextResponse(body, { headers }); // and construct the resulting response now
}
