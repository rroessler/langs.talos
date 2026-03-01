/// Node Modules
import * as fs from 'node:fs';

/// Vendor Modules
import { NextResponse } from 'next/server';

/// Library Modules
import { Assets } from '@/website/assets';

/** Ensure no caching occurs. */
export const revalidate = false;

/** Gets the "install.ps1" script. */
export async function GET() {
    const body = await fs.promises.readFile(Assets.scripts('install.ps1')); // prepare the incoming body
    const headers = { 'Content-Disposition': 'inline; filename="install.ps1"', 'Content-Type': 'text/plain' };
    return new NextResponse(body, { headers }); // and construct the resulting response now
}
